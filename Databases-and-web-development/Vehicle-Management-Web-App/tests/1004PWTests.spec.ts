import exp from 'constants';

//@ts-check
const { test, expect} = require('@playwright/test');

// change this to the URL of your website, could be local or GitHub pages
const websiteURL = 'http://127.0.0.1:5500/coursework/peoplesearch.html';

// Go to the website home page before each test.
test.beforeEach(async ({ page }) => {
   await page.goto(websiteURL);
});

// # html tests

// page links
test('homepage heading', async ({ page }) => {

   // Expect a heading 'People Search"
   await expect(page.getByRole('heading', { name: 'People Search' })).toBeVisible();

});

test('link - vehicle search', async ({ page }) => {

   // Click the 'vehicle search' link.
   await page.getByRole('link', { name: 'Vehicle search' }).click();

   // Expects page to have a heading 'Vehicle search'.
   await expect(page.getByRole('heading', { name: 'Vehicle Search' })).toBeVisible();
});

// head
test('should set the language to English', async ({ page }) => {
   const htmlElement = await page.locator('html');
   await expect(htmlElement).toHaveAttribute('lang','en');
});

// ul for navigation link
test('there is a <ul> inside <header> for navigation links', async ({ page }) => {

   const ulNum = await page.locator('header').locator('ul').count()
   expect(ulNum).toBeGreaterThan(0)

})

// semantic structure elements
test('there is a <header> element', async ({ page }) => {
   const headerNum = await page.locator('header').count()
   expect(headerNum).toBeGreaterThan(0)
})

test('there are three navigation links (<li>)', async ({ page }) => {
   const liNum = await page.locator('header').locator('ul').locator('li').count()
   // console.log(`liNum: ${liNum}`)
   expect(liNum).toBeGreaterThan(2)
})

// there is an image or video in side bar
test('html - image or video', async ({ page }) => {
   const imageNum = await page.locator('aside').locator('img').count()
   const videoNum = await page.locator('aside').locator('video').count()
   expect(imageNum + videoNum).toBeGreaterThan(0)
})

// # CSS tests

// all pages use the same css

test('same external css for all html pages', async ({ page }) => {
   
   const cssFile = await page.locator('link').getAttribute('href')

   await page.getByRole('link', { name: 'Vehicle search' }).click();
   await expect(page.locator('link')).toHaveAttribute('href', cssFile);

   await page.getByRole('link', { name: 'Add a vehicle' }).click();
   await expect(page.locator('link')).toHaveAttribute('href', cssFile);
})

// css flex for navigation links

test('use css flex to place navigation links horizontally', async ({ page }) => {

   await expect(page.locator('header').locator('ul')).toHaveCSS('display', 'flex')

   await expect(page.getByRole('link', { name: 'Vehicle search' })).toHaveCSS('flex', '0 1 auto')

})

// border margin padding

test('header should have padding 10px, margin 10px, and border 1px solid black', async ({ page }) => {
   
   const space = '10px'
   const border = '1px solid rgb(0, 0, 0)'

   await expect(page.locator('header')).toHaveCSS('padding', space)
   await expect(page.locator('header')).toHaveCSS('margin', space)
   await expect(page.locator('header')).toHaveCSS('border', border)
})

// CSS grid

test ('CSS grid is used to layout the page components', async({page}) => {
   await expect(page.locator('#container')).toHaveCSS('display','grid')
})

// # JavaScript Tests

// people search
test ('search "rachel" should return two records', async ({page}) => {
   await page.locator('#name').fill('rachel')
   await page.getByRole('button', { name: 'Submit' }).click();
   await expect(page.locator('#results')).toContainText('SG345PQ')
   await expect(page.locator('#results')).toContainText('JK239GB')
   await expect(page.locator('#results').locator('div')).toHaveCount(2)
   await expect(page.locator('#message')).toContainText('Search successful')
})

// non existent people search
test ('search "ABCDEF" should return no records', async ({page}) => {
   await page.locator('#name').fill('ABCDEF')
   await page.getByRole('button', { name: 'Submit' }).click();
   //await expect(page.locator('#results')).toContainText('SG345PQ')
   //await expect(page.locator('#results')).toContainText('JK239GB')
   await expect(page.locator('#results').locator('div')).toHaveCount(0)
   await expect(page.locator('#message')).toContainText('No result found')
})

// name and license filled
test ('search "rachel" and "KWK24JI" should return error', async ({page}) => {
   await page.locator('#name').fill('rachel')
   await page.locator('#license').fill('KWK24JI')
   await page.getByRole('button', { name: 'Submit' }).click();
   //await expect(page.locator('#results')).toContainText('SG345PQ')
   //await expect(page.locator('#results')).toContainText('JK239GB')
   await expect(page.locator('#results').locator('div')).toHaveCount(0)
   await expect(page.locator('#message')).toContainText('Error')
})

// neither name or license filled
test ('search "" should return error', async ({page}) => {
   //await page.locator('#name').fill('')
   await page.getByRole('button', { name: 'Submit' }).click();
   //await expect(page.locator('#results')).toContainText('SG345PQ')
   //await expect(page.locator('#results')).toContainText('JK239GB')
   await expect(page.locator('#results').locator('div')).toHaveCount(0)
   await expect(page.locator('#message')).toContainText('Error')
})

// case sensitive people search
test ('search "RACHEL" should return two records', async ({page}) => {
   await page.locator('#name').fill('RACHEL')
   await page.getByRole('button', { name: 'Submit' }).click();
   await expect(page.locator('#results')).toContainText('SG345PQ')
   await expect(page.locator('#results')).toContainText('JK239GB')
   await expect(page.locator('#results').locator('div')).toHaveCount(2)
   await expect(page.locator('#message')).toContainText('Search successful')
})

// partial name people search
test ('search "rach" should return two records', async ({page}) => {
   await page.locator('#name').fill('rach')
   await page.getByRole('button', { name: 'Submit' }).click();
   await expect(page.locator('#results')).toContainText('SG345PQ')
   await expect(page.locator('#results')).toContainText('JK239GB')
   await expect(page.locator('#results').locator('div')).toHaveCount(2)
   await expect(page.locator('#message')).toContainText('Search successful')
})

// vehicle search
test('search "KWK24JI" should return tesla but no owner', async ({page}) => {
   await page.getByRole('link', { name: 'Vehicle search' }).click();
   await page.locator('#rego').fill('KWK24JI')
   await page.getByRole('button', { name: 'Submit' }).click();
   await expect(page.locator('#results')).toContainText('Tesla')
   await expect(page.locator('#results').locator('div')).toHaveCount(1)
   await expect(page.locator('#message')).toContainText('Search successful')
})

// case sensitive vehicle search
test('search "kwk24ji" should return tesla but no owner', async ({page}) => {
   await page.getByRole('link', { name: 'Vehicle search' }).click();
   await page.locator('#rego').fill('kwk24ji')
   await page.getByRole('button', { name: 'Submit' }).click();
   await expect(page.locator('#results')).toContainText('Tesla')
   await expect(page.locator('#results').locator('div')).toHaveCount(1)
   await expect(page.locator('#message')).toContainText('Search successful')
})

// case sensitive vehicle search
test('search "kwk2" should return tesla but no owner', async ({page}) => {
   await page.getByRole('link', { name: 'Vehicle search' }).click();
   await page.locator('#rego').fill('kwk2')
   await page.getByRole('button', { name: 'Submit' }).click();
   await expect(page.locator('#results')).toContainText('Tesla')
   await expect(page.locator('#results').locator('div')).toHaveCount(1)
   await expect(page.locator('#message')).toContainText('Search successful')
})

// non existent vehicle search
test('search "ABCDEFG" should return No result found', async ({page}) => {
   await page.getByRole('link', { name: 'Vehicle search' }).click();
   await page.locator('#rego').fill('ABCDEFG')
   await page.getByRole('button', { name: 'Submit' }).click();
   //await expect(page.locator('#results')).toContainText('Tesla')
   await expect(page.locator('#results').locator('div')).toHaveCount(0)
   await expect(page.locator('#message')).toContainText('No result found')
})

// no rego entered
test('search "" should return Error', async ({page}) => {
   await page.getByRole('link', { name: 'Vehicle search' }).click();
   //await page.locator('#rego').fill('')
   await page.getByRole('button', { name: 'Submit' }).click();
   //await expect(page.locator('#results')).toContainText('Tesla')
   await expect(page.locator('#results').locator('div')).toHaveCount(0)
   await expect(page.locator('#message')).toContainText('Error')
})


// add a vehicle (missing owner)
test('add a vehicle and owner', async ({page}) => {
   await page.getByRole('link', { name: 'Add a vehicle' }).click();
   await page.locator('#rego').fill('R4D6G9K')
   await page.locator('#make').fill('Mclaren')
   await page.locator('#model').fill('Seven')
   await page.locator('#colour').fill('Red')
   await page.locator('#owner').fill('Lizzy')
   await page.getByRole('button', { name: 'Check owner' }).click();

   // expect a 'New owner' button
   await expect(page.getByRole('button', { name: 'New owner' })).toBeVisible()

   // click the 'New owner' button
   await page.getByRole('button', { name: 'New owner' }).click();

   // add a new person
   await page.locator('#name').fill('Lizzy')
   await page.locator('#address').fill('Manchester')
   await page.locator('#dob').fill('1991-04-09')
   await page.locator('#license').fill('5TRHJW')
   await page.locator('#expire').fill('2031-01-01')
   await page.getByRole('button', { name: 'Add owner' }).click();
   await expect(page.locator('#message-owner')).toContainText('Owner added successfully')

   await page.getByRole('button', { name: 'Add vehicle' }).click();
   await expect(page.locator('#message-vehicle')).toContainText('Vehicle added successfully')

   await page.getByRole('link', { name: 'People search' }).click();
   await page.locator('#name').fill('Lizzy')
   await page.getByRole('button', { name: 'Submit' }).click();
   await expect(page.locator('#results')).toContainText('5TRHJW')
   await expect(page.locator('#results').locator('div')).toHaveCount(1)
})

// check button not enabled till owner is not NULL
test('check button is disabled when owner field empty', async ({page}) => {
   await page.getByRole('link', { name: 'Add a vehicle' }).click();
   const checkButton = page.getByRole('button', { name: 'Check owner' });
   await page.locator('#owner').fill('');
   await expect(checkButton).toBeDisabled();
})

// partial match and case sensitive
test('check a capital owner', async ({page}) => {
   await page.getByRole('link', { name: 'Add a vehicle' }).click();
   await page.locator('#rego').fill('LKJ23UO')
   await page.locator('#make').fill('Porsche')
   await page.locator('#model').fill('Taycan')
   await page.locator('#colour').fill('white')
   await page.locator('#owner').fill('DAPHNE LAI')
   await page.getByRole('button', { name: 'Check owner' }).click();
   await expect(page.locator('#owner-results').locator('div')).toHaveCount(1)
   await expect(page.locator('#message-vehicle')).toContainText('Search successful')
})
test('check a partial owner', async ({page}) => {
   await page.getByRole('link', { name: 'Add a vehicle' }).click();
   await page.locator('#rego').fill('LKJ23UO')
   await page.locator('#make').fill('Porsche')
   await page.locator('#model').fill('Taycan')
   await page.locator('#colour').fill('white')
   await page.locator('#owner').fill('Daph')
   await page.getByRole('button', { name: 'Check owner' }).click();
   await expect(page.locator('#owner-results').locator('div')).toHaveCount(1)
   await expect(page.locator('#message-vehicle')).toContainText('Search successful')
})

// add a vehicle (existing owner)
test('add a vehicle existing owner', async ({page}) => {
   await page.getByRole('link', { name: 'Add a vehicle' }).click();
   await page.locator('#rego').fill('ABCDR456')
   await page.locator('#make').fill('BMW')
   await page.locator('#model').fill('L')
   await page.locator('#colour').fill('Blue')
   await page.locator('#owner').fill('Daphne Lai')
   await page.getByRole('button', { name: 'Check owner' }).click();

   // expect a 'New owner' button
   await expect(page.getByRole('button', { name: 'Select owner' })).toBeVisible()

   // click the 'New owner' button
   await page.getByRole('button', { name: 'Select owner' }).click();

   await expect(page.locator('#message-vehicle')).toContainText('Vehicle added successfully')

})

// add an empty field vehicle
test('add a null field vehicle', async ({page}) => {
   await page.getByRole('link', { name: 'Add a vehicle' }).click();
   await page.locator('#rego').fill('LKJ23UO')
   await page.locator('#make').fill('')
   await page.locator('#model').fill('Taycan')
   await page.locator('#colour').fill('white')
   await page.locator('#owner').fill('Daphne Lai')
   await page.getByRole('button', { name: 'Check owner' }).click();

   await expect(page.locator('#message-vehicle')).toContainText('Error')

})

// add an owner (existing owner)
test('add an existing owner', async ({page}) => {
   await page.getByRole('link', { name: 'Add a vehicle' }).click();
   await page.locator('#rego').fill('LKJ23UO')
   await page.locator('#make').fill('Porsche')
   await page.locator('#model').fill('Taycan')
   await page.locator('#colour').fill('white')
   await page.locator('#owner').fill('Daphne Lai')
   await page.getByRole('button', { name: 'Check owner' }).click();

   // expect a 'New owner' button
   await expect(page.getByRole('button', { name: 'New owner' })).toBeVisible()

   // click the 'New owner' button
   await page.getByRole('button', { name: 'New owner' }).click();

   // add a new person
   await page.locator('#name').fill('Daphne Lai')
   await page.locator('#address').fill('Leicester')
   await page.locator('#dob').fill('1980-08-13')
   await page.locator('#license').fill('DL890GB')
   await page.locator('#expire').fill('2017-06-24')
   await page.getByRole('button', { name: 'Add owner' }).click();
   await expect(page.locator('#message-owner')).toContainText('Error')
})

// add an owner empty fields
test('add an owner with empty fields', async ({page}) => {
   await page.getByRole('link', { name: 'Add a vehicle' }).click();
   await page.locator('#rego').fill('LKJ23UO')
   await page.locator('#make').fill('Porsche')
   await page.locator('#model').fill('Taycan')
   await page.locator('#colour').fill('white')
   await page.locator('#owner').fill('Kai')
   await page.getByRole('button', { name: 'Check owner' }).click();

   // expect a 'New owner' button
   await expect(page.getByRole('button', { name: 'New owner' })).toBeVisible()

   // click the 'New owner' button
   await page.getByRole('button', { name: 'New owner' }).click();

   // add a new person
   await page.locator('#name').fill('Kai')
   await page.locator('#address').fill('')
   await page.locator('#dob').fill('')
   await page.locator('#license').fill('')
   await page.locator('#expire').fill('')
   await page.getByRole('button', { name: 'Add owner' }).click();
   await expect(page.locator('#message-owner')).toContainText('Error')
})